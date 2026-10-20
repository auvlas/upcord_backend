CREATE TABLE chat (
    id          BIGINT      PRIMARY KEY AUTOINCREMENT,
    name        VARCHAR(50) NOT NULL,
    chatname    VARCHAR(50) DEFAULT NULL UNIQUE,
    description TEXT        DEFAULT NULL,
    created_at  DATETIME    DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX idx_chat_chatname ON char(chatname)
