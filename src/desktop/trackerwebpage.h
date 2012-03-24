#ifndef TRACKERWEBPAGE_H
#define TRACKERWEBPAGE_H

#include <QWebPage>

class TrackerWebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit TrackerWebPage(QObject *parent = 0);
    virtual QString userAgentForUrl(const QUrl& url) const;
    
signals:
    
public slots:
    
};

#endif // TRACKERWEBPAGE_H
