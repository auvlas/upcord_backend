#include <QtTypes>
#include <QString>
#include <optional>
#include <utility>


namespace Database {
    namespace Models {
        class User {
        private:
            qint64 m_id{0};
            QString m_visibleName{};
            QString m_userName{};
            // QString m_hashPassword{};
            QString m_firstName{};
            QString m_secondName{};
            QString m_fatherName{};
            QString m_email{};
            QString m_phone{};
            // QList<QString> m_activeSessionJwt{};

            explicit User(qint64 id);

        public:
            static std::optional<std::pair<User, QString> loginUserName(
                    QString userName, QString password);

            static std::optional<std::pair<User, QString> loginEmail(
                    QString userName, QString password);

            static std::optional<std::pair<User, QString> loginPhone(
                    QString userName, QString password);

            static std::pair<User, QString> create(QString visibleName,
                    QString userName, QString password, QString firstName,
                    QString secondName, QString fatherName,
                    QString email, QString phone);

            static std::optional<std::pair<User, QString>> login(
                    QString UEP, QString password);

            static std::pair<QList<Server>, QList<DirectMessage>> login(QString jwt);

            static QJsonObject create(QJsonObject newUser);

            static QJsonObject login(QJsonObject authorizationData);

            QJsonObject getJson() const;
        };
    }
}
