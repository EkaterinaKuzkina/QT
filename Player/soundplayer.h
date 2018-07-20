#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#pragma once
#include <QWidget>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QListWidget>
#include <QSettings>
#include <QMessageBox>

class soundplayer: public QWidget{
    Q_OBJECT
protected:
    QMediaPlayer*   m_pmp;
    QMediaPlaylist* playlist;
    QMediaPlaylist* playlist_pic;
    QVBoxLayout*    m_pvbxMainLayout;
private:
    QPushButton* m_pcmdPlay;
    QPushButton* m_pcmdStop;
    QSlider*     m_psldPosition;
    QSlider*     psldVolume;
    QLabel*      m_plblCurrent;
    QLabel*      m_plblRemain;
    QLabel*      Image_Label;
    QListWidget* m_lLwidg;
    QListWidget* m_picwidg;
    typedef QList<QImage> QImageList;
    QImageList imageList;
    QTimer *timer;
    QSettings settings;
    int iter=0, time=10000;
    QList<QMediaContent> content_pic;

    QString msecsToString(qint64 n);

public:
    soundplayer(QWidget* pwgt = 0);

private slots:
    void slotOpen               ();
    void slotPlay               ();
    void slotSetSliderPosition  (qint64);
    void slotSetMediaPosition   (int);
    void slotSetDuration        (qint64);
    void slotStatusChanged      (QMediaPlayer::State);
    void onListDoubleClicked    (const QModelIndex&);
    void getNext                ();
    void getPrev                ();
    void slotOpenPic            ();
    void onListDoubleClickedPic (const QModelIndex&);
    void setImageLabel          ();
    void stop_timer             ();
    void setTimeForTimer_50     ();
    void setTimeForTimer_30     ();
    void setTimeForTimer_20     ();
    void on_saveButton_clicked  ();
    void setPrevSets            ();
};


#endif // SOUNDPLAYER_H
