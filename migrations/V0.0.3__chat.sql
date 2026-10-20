CREATE TABLE chat (
    id          BIGINT      PRIMARY KEY AUTOINCREMENT,
    rule_id     BIGINT      NOT NULL,
    chat_id     BIGINT      NOT NULL,
    name        VARCHAR(50) NOT NULL,
    chatname    VARCHAR(50) DEFAULT NULL UNIQUE,
    avatar      TEXT        DEFAULT NULL,
    description TEXT        DEFAULT NULL,
    created_at  DATETIME    DEFAULT CURRENT_TIMESTAMP,

    FOREING KEY (rule_id)   REFERENCE chat_rule(id),
    FOREING KEY (chat_id)   REFERENCE chat_member(id)
);

CREATE INDEX idx_chat_chatname ON char(chatname)
