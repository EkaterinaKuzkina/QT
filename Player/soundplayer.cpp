#include "soundplayer.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QIcon>
#include <QTime>
#include <QMediaPlaylist>
#include <QImage>
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>

soundplayer::soundplayer(QWidget *pwgt):QWidget(pwgt) //конструктор
{
    QPushButton* pcmdOpen       = new QPushButton ("&Add Music");
    QPushButton* Nextbutton     = new QPushButton();
    QPushButton* Previousbutton = new QPushButton();
    QPushButton* OpenIm         = new QPushButton("&Add Image");
    QPushButton* sec_50         = new QPushButton("&50");
    QPushButton* sec_30         = new QPushButton("&30");
    QPushButton* sec_20         = new QPushButton("&20");
    QPushButton* save_set       = new QPushButton("&Save");
    QPushButton* set_back       = new QPushButton("&Previous settings");


    m_pcmdPlay     = new QPushButton;
    m_pcmdStop     = new QPushButton;
    m_psldPosition = new QSlider;
    m_plblCurrent  = new QLabel (msecsToString(0));
    m_plblRemain   = new QLabel(msecsToString(0));
    m_pmp          = new QMediaPlayer();
    playlist       = new QMediaPlaylist(m_pmp);
    m_lLwidg       = new QListWidget;
    m_picwidg      = new QListWidget;
    Image_Label    = new QLabel;
    timer          = new QTimer(this);
    psldVolume     = new QSlider;

    m_pmp->setPlaylist(playlist);
    m_pcmdPlay->setEnabled(false);
    m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    Nextbutton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    Previousbutton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    m_pcmdStop->setEnabled(false);
    m_pcmdStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    m_psldPosition->setRange(0, 0);
    m_psldPosition->setOrientation(Qt::Horizontal);

    psldVolume->setRange(0,100);
    int nDefaultVolume = 50;
    m_pmp->setVolume(nDefaultVolume);
    psldVolume->setValue(nDefaultVolume);

    connect(pcmdOpen, SIGNAL(clicked()), SLOT(slotOpen()));
    connect(m_pcmdPlay, SIGNAL(clicked()), SLOT(slotPlay()));
    connect(m_pcmdStop, SIGNAL(clicked()), m_pmp, SLOT(stop()));
    connect(psldVolume,SIGNAL(valueChanged(int)), m_pmp, SLOT(setVolume(int)));
    connect(m_psldPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPosition(int)));
    connect(m_pmp, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(m_pmp, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(m_pmp, SIGNAL(stateChanged(QMediaPlayer::State)), SLOT(slotStatusChanged(QMediaPlayer::State)));
    connect(m_lLwidg, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListDoubleClicked(QModelIndex)));
    connect(Nextbutton, SIGNAL(clicked(bool)), this, SLOT(getNext()));
    connect(Previousbutton, SIGNAL(clicked(bool)), this, SLOT(getPrev()));
    connect(OpenIm, SIGNAL(clicked(bool)), this, SLOT(slotOpenPic()));
    connect(m_picwidg, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListDoubleClickedPic(QModelIndex)));
    connect(timer, SIGNAL(timeout()), this, SLOT(setImageLabel()));
    connect(m_pcmdStop, SIGNAL(clicked(bool)), this, SLOT(stop_timer()));
    connect(sec_50, SIGNAL(clicked(bool)), this, SLOT(setTimeForTimer_50()));
    connect(sec_30, SIGNAL(clicked(bool)), this, SLOT(setTimeForTimer_30()));
    connect(sec_20, SIGNAL(clicked(bool)), this, SLOT(setTimeForTimer_20()));
    connect(save_set, SIGNAL(clicked(bool)), this, SLOT(on_saveButton_clicked()));
    connect(set_back, SIGNAL(clicked(bool)), this, SLOT(setPrevSets()));

    QVBoxLayout* timeChoose = new QVBoxLayout;
    timeChoose->addWidget(sec_50);
    timeChoose->addWidget(sec_30);
    timeChoose->addWidget(sec_20);

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(psldVolume);
    topLayout->addWidget(Image_Label);
    topLayout->addLayout(timeChoose);

    QVBoxLayout* saveControl = new QVBoxLayout;
    saveControl->addWidget(save_set);
    saveControl->addWidget(set_back);
    saveControl->addWidget(pcmdOpen);
    saveControl->addWidget(OpenIm);

    QHBoxLayout* midLayout = new QHBoxLayout;
    midLayout->addWidget(m_lLwidg);
    midLayout->addWidget(m_picwidg);
    midLayout->addLayout(saveControl);

    QHBoxLayout* phbxTimeControls = new QHBoxLayout;
    phbxTimeControls->addWidget(m_plblCurrent);
    phbxTimeControls->addWidget(m_psldPosition);
    phbxTimeControls->addWidget(m_plblRemain);

    QHBoxLayout* phbxPlayControls = new QHBoxLayout;
    phbxPlayControls->addWidget(Previousbutton);
    phbxPlayControls->addWidget(m_pcmdPlay);
    phbxPlayControls->addWidget(m_pcmdStop);
    phbxPlayControls->addWidget(Nextbutton);

    m_pvbxMainLayout= new QVBoxLayout;
    m_pvbxMainLayout->addLayout(topLayout);
    m_pvbxMainLayout->addLayout(midLayout);
    m_pvbxMainLayout->addLayout(phbxTimeControls);
    m_pvbxMainLayout->addLayout(phbxPlayControls);

    setLayout(m_pvbxMainLayout);
}

void soundplayer::setPrevSets()
{
    m_lLwidg->clear();
    m_picwidg->clear();
    playlist->clear();
    QFile file("/Users/ekaterinakuzkina/Player_1/muz_file.txt");
     if (!file.exists())
         qDebug()<<"error!";
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         qDebug()<<"error!!";

    QTextStream in(&file);
    QList<QMediaContent> content;
    QString ss;
    while (!in.atEnd())
    {
        ss=in.readLine();
        content.push_back(QUrl::fromUserInput(ss));
        QFileInfo fi(ss);
        m_lLwidg->addItem(fi.fileName());
    }
    playlist->addMedia(content);
    if (m_lLwidg->count()!=0)
    {
        m_pcmdPlay->setEnabled(true);
        m_pcmdStop->setEnabled(true);
        playlist->setCurrentIndex(0);
        m_lLwidg->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
    }
    file.close();

    QFile file_pic("/Users/ekaterinakuzkina/Player_1/pic_file.txt");
     if (!file_pic.exists())
         qDebug()<<"error*";
     if (!file_pic.open(QIODevice::ReadOnly | QIODevice::Text))
         qDebug()<<"error**";

    QTextStream in_pic(&file_pic);
    QString ss_pic;
    while (!in_pic.atEnd())
    {
         ss_pic=in_pic.readLine();
         content_pic.push_back(QUrl::fromUserInput(ss_pic));
         imageList.push_back(QImage(ss_pic.remove(0,7)));
         QFileInfo fi_pic(ss_pic);
         m_picwidg->addItem(fi_pic.fileName());
     }
    file_pic.close();

    QFile file_set("/Users/ekaterinakuzkina/Player_1/set_file.txt");
    if (!file_set.exists())
        qDebug()<<"error%";
    if (!file_set.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"error%%";
    QTextStream in_set(&file_set);
    QString ss_set;
    time=in_set.readLine().toInt() ;
    psldVolume->setValue(in_set.readLine().toInt());
    file_set.close();
}

void soundplayer::on_saveButton_clicked()
{
    QFile file("/Users/ekaterinakuzkina/Player_1/muz_file.txt");
    if (!file.open(QFile::WriteOnly|QFile::Truncate))
        qDebug()<<"error?";
    QTextStream out(&file);
    for (int i=0; i<m_lLwidg->count(); i++)
    {
        if(playlist->media(i)==playlist->currentMedia())
        {
            out<<playlist->media(i).canonicalUrl().toString()<<endl;
        }
    }
    for (int i=0; i<m_lLwidg->count(); i++)
    {
        if(playlist->media(i)!=playlist->currentMedia())
        {
            out<<playlist->media(i).canonicalUrl().toString()<<endl;
        }
    }
    file.close();

    QFile file_pic("/Users/ekaterinakuzkina/Player_1/pic_file.txt");
    if (!file_pic.open(QFile::WriteOnly|QFile::Truncate))
          qDebug()<<"omg";

    QTextStream out_pic(&file_pic);
    for (int i=0; i<m_picwidg->count(); i++)
    {
         out_pic<<content_pic.value(i).canonicalUrl().toString()<<endl;
    }
    file_pic.close();

    QFile file_set("/Users/ekaterinakuzkina/Player_1/set_file.txt");
    if (!file_set.open(QFile::WriteOnly|QFile::Truncate))
        qDebug()<<"omg";

    QTextStream out_set(&file_set);
    out_set<<time<<endl;
    out_set<<psldVolume->value()<<endl;
    file_set.close();

    QMessageBox::information(this, "Save Settings", "Save Done!");
}

void soundplayer::setTimeForTimer_50()
{
    time=50000;
}

void soundplayer::setTimeForTimer_30()
{
    time=30000;
}

void soundplayer::setTimeForTimer_20()
{
    time=20000;
}

void soundplayer::stop_timer()
{
    timer->stop();
}

void soundplayer::setImageLabel()
{
    if (imageList.count()==0)
        Image_Label->setText("Pictures are not existed");
    else
    {
        QSize PicSize(400, 500);
        if (iter==imageList.count())
        {
            iter=0;
        }
        Image_Label->setPixmap((QPixmap::fromImage(imageList[iter])).scaled(PicSize, Qt::KeepAspectRatio));
        iter++;
    }
}


void soundplayer::slotOpen()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"Open File");
    QList<QMediaContent> content;
    for(const QString& f:files)
    {
        content.push_back(QUrl::fromLocalFile(f));
        QFileInfo fi(f);
        m_lLwidg->addItem(fi.fileName());
    }
    playlist->addMedia(content);
    m_pcmdPlay->setEnabled(true);
    m_pcmdStop->setEnabled(true);
    playlist->setCurrentIndex(0);
    m_lLwidg->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
}

void soundplayer::slotOpenPic()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"Open File");
    for(const QString& f_pic:files)
    {
        content_pic.push_back(QUrl::fromLocalFile(f_pic));
        imageList.push_back(QImage(f_pic));
        QFileInfo fi_pic(f_pic);
        m_picwidg->addItem(fi_pic.fileName());
    }
}

void soundplayer::onListDoubleClickedPic(const QModelIndex& index)
{
    if (!index.isValid())
    {
        return;
    }

    if  ( QListWidget *m_picwidg = dynamic_cast<QListWidget*>(sender()))
    {
        QListWidgetItem* item =m_picwidg->currentItem();
        {
            int k=m_picwidg->currentRow();
            if (k==-1)
            {
                imageList.clear();
                timer->stop();
                content_pic.clear();
                m_picwidg->clear();
                qDebug()<<k;
            }
            else
            {
                delete item;
                imageList.removeAt(k);
                content_pic.removeAt(k);

                if (k==0)
                    iter=1;
            }
        }
    }
}

void soundplayer::getNext()
{
    playlist->next();
    m_lLwidg->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
}

void soundplayer::getPrev()
{
    playlist->previous();
    m_lLwidg->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
}

void soundplayer::onListDoubleClicked(const QModelIndex& index)
{
    if (!index.isValid())
    {
        return;
    }
    if  ( QListWidget *m_lLwidg = dynamic_cast<QListWidget*>(sender()))
    {
        if(QListWidgetItem* item = m_lLwidg->takeItem(index.row()))
        {
            if (m_lLwidg->currentRow()==-1)
            {
                m_pcmdPlay->setEnabled(false);
                playlist->clear();
            }
            int k=m_lLwidg->currentRow();
            playlist->removeMedia(k);
            delete item;
        }
    }
}

void soundplayer::slotPlay()
{
    switch (m_pmp->state())
    {
    case QMediaPlayer::PlayingState:
        m_pmp->pause();
        timer->stop();
        break;
    default:
        m_pmp->play();
        if (imageList.size()!=0)
        {
            timer->start(time);
            setImageLabel();
        }
        m_lLwidg->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);
        break;
    }
}

void soundplayer::slotStatusChanged(QMediaPlayer::State state)
{
    switch (state)
    {
    case QMediaPlayer::PlayingState:
        m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        timer->stop();
        break;
    }
}

void soundplayer::slotSetMediaPosition(int n)
{
    m_pmp->setPosition(n);
}

QString soundplayer::msecsToString(qint64 n) //отображение времени песни
{
    int nHours = (n/(60*60*1000));
    int nMinutes = ((n % (60*60*1000)) / (60*1000));
    int nSeconds = ((n % (60*1000)) / 1000);

    return QTime (nHours, nMinutes, nSeconds).toString("hh::mm::ss");
}
//устанавливаем максимальное значение ползунка
void soundplayer::slotSetDuration(qint64 n)
{
    m_psldPosition->setRange(0,n);
    m_plblCurrent->setText(msecsToString(0));
    m_plblRemain->setText(msecsToString(n));
}

void soundplayer::slotSetSliderPosition(qint64 n)
{
    m_psldPosition->setValue(n);
    m_plblCurrent->setText(msecsToString(n));
    int nDuration = m_psldPosition->maximum();
    m_plblRemain->setText(msecsToString(nDuration-n));
    m_lLwidg->setCurrentRow(playlist->currentIndex() != -1? playlist->currentIndex():0);

}
