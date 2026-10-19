CREATE TABLE user (
    id            INTEGER  PRIMARY KEY AUTOINCREMENT,
    username      TEXT     NOT NULL UNIQUE,
    email         TEXT,
    phone         TEXT,
    password_hash TEXT     NOT NULL,
    created_at    DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_user_username ON user(username);
CREATE INDEX idx_user_email    ON user(email);
CREATE INDEX idx_user_phone    ON user(phone);
