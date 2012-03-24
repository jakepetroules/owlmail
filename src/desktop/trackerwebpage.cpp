#include "trackerwebpage.h"

TrackerWebPage::TrackerWebPage(QObject *parent) :
    QWebPage(parent)
{
}

QString TrackerWebPage::userAgentForUrl(const QUrl& url) const
{
    Q_UNUSED(url);
    return QString("Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_3) AppleWebKit/534.53.11 (KHTML, like Gecko) Version/5.1.3 Safari/534.53.10");
}
