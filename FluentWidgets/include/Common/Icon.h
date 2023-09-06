#ifndef __ICON_H
#define __ICON_H

#include "Config.h"
#include <QIconEngine>

namespace FW {

/**
 * @brief 图标绘制引擎，每个需要Icon的Widget都需要Icon引擎
 *
 */
class IconEngine : public QIconEngine {
public:
    IconEngine(const QString &path);

    QString iconPath();
    void setIconPath(const QString &path);

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) override;
    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) override;
    QIconEngine *clone() const override;

private:
    QString m_iconPath;
    bool m_isSvg;
};

/**
 * @brief FlunetICon的基类
 *
 */
class FluentIconBase : public QObject {
    Q_OBJECT
public:
    explicit FluentIconBase(const QString &path, bool reg = true);
    virtual ~FluentIconBase();

    virtual QIcon icon()             = 0;
    virtual QString typeName() const = 0;
    virtual QString enumName() const = 0;
    virtual FluentIconBase *clone()  = 0;

    virtual void setTheme(const FW::Theme &theme) = 0;

    virtual void render(QPainter *painter, const QRect &rect, const QVector<int> &indexes = QVector<int>(),
                        const QHash<QString, QString> &attributes = QHash<QString, QString>());

    QScopedPointer<IconEngine> m_iconEngine;
};

class FluentIcon : public FluentIconBase {
    Q_OBJECT
public:
    enum IconType {
        Unknown = -1,
        Add     = 0,
        Cut,
        Pin,
        Tag,
        Chat,
        Copy,
        Code,
        Edit,
        Font,
        Help,
        Hide,
        Home,
        Info,
        Link,
        Mail,
        Menu,
        More,
        Save,
        Send,
        Sync,
        View,
        Zoom,
        Album,
        Brush,
        Close,
        Embed,
        Globe,
        Heart,
        Media,
        Movie,
        Music,
        Paste,
        Photo,
        Phone,
        Print,
        Share,
        Unpin,
        Video,
        Accept,
        Camera,
        Cancel,
        Delete,
        Folder,
        Scroll,
        Layout,
        GitHub,
        Update,
        Return,
        Ringer,
        Search,
        SaveAs,
        ZoomIn,
        History,
        Setting,
        Palette,
        Message,
        ZoomOut,
        Feedback,
        Minimize,
        CheckBox,
        Document,
        Language,
        Download,
        Question,
        DateTime,
        SendFill,
        Completed,
        Luminance,
        Alignment,
        BookShelf,
        Highlight,
        FolderAdd,
        PencilInk,
        ZipFolder,
        Microphone,
        ChevronDown,
        Transparent,
        MusicFolder,
        ChevronRight,
        BackgroundFill
    };

    Q_ENUM(IconType)
    static QString iconName(IconType type);

    explicit FluentIcon(const QString &customPath, bool reg = true);
    explicit FluentIcon(IconType type, Theme t = Theme::AUTO, bool reg = true);
    ~FluentIcon();

    QIcon icon() override;
    QString typeName() const override;
    QString enumName() const override;
    FluentIcon *clone() override;
    QString iconPath();
    QString getIconColor();

    void setTheme(const FW::Theme &theme) override;
    Theme theme() const;

private:
    Theme m_theme;
    IconType m_type;
};
}  // namespace FW

#endif