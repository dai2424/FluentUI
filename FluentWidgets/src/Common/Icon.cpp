#include "Icon.h"
#include "../FluentWidget.h"
#include <QMetaEnum>
#include <QPainter>
#include <QSvgRenderer>

using namespace FW;

IconEngine::IconEngine(const QString &path)
    : QIconEngine(), m_iconPath(path) {
    // 判断资源类型
    m_isSvg = m_iconPath.toLower().endsWith(".svg");
}

QString IconEngine::iconPath() {
    return m_iconPath;
}

void FW::IconEngine::setIconPath(const QString &path) {
    m_iconPath = path;
}

void IconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) {
    if(m_iconPath.isEmpty()) return;

    // 提升绘画质量
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    if(m_isSvg) {
        QSvgRenderer svgRender(m_iconPath);
        svgRender.render(painter, QRectF(rect));
    }
    else {
        QPixmap pixmap = QIcon(m_iconPath).pixmap(rect.width(), rect.height());
        painter->drawPixmap(rect, pixmap);
    }
}

QPixmap IconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) {
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    paint(&painter, QRect(QPoint(0, 0), size), mode, state);

    return pixmap;
}

QIconEngine *IconEngine::clone() const {
    return new IconEngine(m_iconPath);
}
/** FlunetIconBase's implementation **/
FluentIconBase::FluentIconBase(const QString &path)
    : m_iconEngine(new IconEngine(path)) {
}

FluentIconBase::~FluentIconBase() {
}

void FluentIconBase::render(QPainter *painter, const QRect &rect, const QVector<int> &indexes, const QHash<QString, QString> &attributes) {
    m_iconEngine->paint(painter, rect, QIcon::Normal, QIcon::On);
}

QString FluentIcon::iconName(IconType type) {
    switch(type) {
        case Unknown:
            return "Unknown";
        case Add:
            return "Add";
        case Cut:
            return "Cut";
        case Pin:
            return "Pin";
        case Tag:
            return "Tag";
        case Chat:
            return "Chat";
        case Copy:
            return "Copy";
        case Code:
            return "Code";
        case Edit:
            return "Edit";
        case Font:
            return "Font";
        case Help:
            return "Help";
        case Hide:
            return "Hide";
        case Home:
            return "Home";
        case Info:
            return "Info";
        case Link:
            return "Link";
        case Mail:
            return "Mail";
        case Menu:
            return "Menu";
        case More:
            return "More";
        case Save:
            return "Save";
        case Send:
            return "Send";
        case Sync:
            return "Sync";
        case View:
            return "View";
        case Zoom:
            return "Zoom";
        case Album:
            return "Album";
        case Brush:
            return "Brush";
        case Close:
            return "Close";
        case Embed:
            return "Embed";
        case Globe:
            return "Globe";
        case Heart:
            return "Heart";
        case Media:
            return "Media";
        case Movie:
            return "Movie";
        case Music:
            return "Music";
        case Paste:
            return "Paste";
        case Photo:
            return "Photo";
        case Phone:
            return "Phone";
        case Print:
            return "Print";
        case Share:
            return "Share";
        case Unpin:
            return "Unpin";
        case Video:
            return "Video";
        case Accept:
            return "Accept";
        case Camera:
            return "Camera";
        case Cancel:
            return "Cancel";
        case Delete:
            return "Delete";
        case Folder:
            return "Folder";
        case Scroll:
            return "Scroll";
        case Layout:
            return "Layout";
        case GitHub:
            return "GitHub";
        case Update:
            return "Update";
        case Return:
            return "Return";
        case Ringer:
            return "Ringer";
        case Search:
            return "Search";
        case SaveAs:
            return "SaveAs";
        case ZoomIn:
            return "ZoomIn";
        case History:
            return "History";
        case Setting:
            return "Setting";
        case Palette:
            return "Palette";
        case Message:
            return "Message";
        case ZoomOut:
            return "ZoomOut";
        case Feedback:
            return "Feedback";
        case Minimize:
            return "Minimize";
        case CheckBox:
            return "CheckBox";
        case Document:
            return "Document";
        case Language:
            return "Language";
        case Download:
            return "Download";
        case Question:
            return "Question";
        case DateTime:
            return "DateTime";
        case SendFill:
            return "SendFill";
        case Completed:
            return "Completed";
        case Luminance:
            return "Luminance";
        case Alignment:
            return "Alignment";
        case BookShelf:
            return "BookShelf";
        case Highlight:
            return "Highlight";
        case FolderAdd:
            return "FolderAdd";
        case PencilInk:
            return "PencilInk";
        case ZipFolder:
            return "ZipFolder";
        case Microphone:
            return "Microphone";
        case ChevronDown:
            return "ChevronDown";
        case Transparent:
            return "Transparent";
        case MusicFolder:
            return "MusicFolder";
        case ChevronRight:
            return "ChevronRight";
        case BackgroundFill:
            return "BackgroundColor";
    }
}

FluentIcon::FluentIcon(const QString &customPath)
    : FluentIconBase(customPath), m_theme(Theme::AUTO), m_type(Unknown) {
}

FluentIcon::FluentIcon(IconType type, Theme t)
    : FluentIconBase(""), m_theme(t), m_type(type) {
    m_iconEngine->setIconPath(iconPath());
}

FluentIcon::~FluentIcon() {
}

QIcon FluentIcon::icon() {
    return QIcon(m_iconEngine->clone());
}

QString FluentIcon::typeName() const {
    return iconName(m_type);
}

QString FluentIcon::enumName() const {
    QMetaEnum metaEnum = QMetaEnum::fromType<IconType>();
    return metaEnum.valueToKey(m_type);
}

FluentIcon *FluentIcon::clone() {
    if(m_type == Unknown) {
        return new FluentIcon(m_iconEngine->iconPath());
    }

    return new FluentIcon(m_type, m_theme);
}

QString FluentIcon::iconPath() {
    if(m_type == Unknown) {
        return "";
    }

    QString color;
    if(m_theme == Theme::AUTO) {
        color = getIconColor();
    }
    else if(m_theme == Theme::LIGHT) {
        color = "white";
    }
    else {
        color = "black";
    }

    return QString(":fluentwidgets/images/icons/%1_%2.svg").arg(iconName(m_type)).arg(color);
}

QString FluentIcon::getIconColor() {
    if(FWIns.isDark()) {
        return "white";
    }
    else {
        return "black";
    }
}

void FluentIcon::setTheme(const Theme &theme) {
    m_theme = theme;
    m_iconEngine->setIconPath(this->iconPath());
}

Theme FluentIcon::theme() const {
    return Theme();
}
