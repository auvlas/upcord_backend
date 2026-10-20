CREATE TABLE user (
    id            BIGINT       PRIMARY KEY AUTOINCREMENT,
    username      VARCHAR(50)  DEFAULT NULL UNIQUE,
    email         VARCHAR(254) DEFAULT NULL,
    phone         VARCHAR(15)  DEFAULT NULL,
    password_hash VARCHAR(255) NOT NULL
);

CREATE INDEX idx_user_username ON user(username);
CREATE INDEX idx_user_email    ON user(email);
CREATE INDEX idx_user_phone    ON user(phone);
