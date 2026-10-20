CREATE TABLE chat (
    id          BIGINT      PRIMARY KEY AUTOINCREMENT,
    rule_id     BIGINT      DEFAULT NULL,
    chat_id     BIGINT      DEFAULT NULL,
    server_id   BIGINT      DEFAULT NULL,
    name        VARCHAR(50) NOT NULL,
    chatname    VARCHAR(50) DEFAULT NULL UNIQUE,
    avatar      TEXT        DEFAULT NULL,
    description TEXT        DEFAULT NULL,
    created_at  DATETIME    DEFAULT CURRENT_TIMESTAMP,

    CONSTRAINT chk_chat_valid_combinations CHECK (
        (rule_id IS NOT NULL OR chat_id IS NOT NULL OR server_id IS NOT NULL) 
        AND (chat_id IS NULL OR server_id IS NULL)
    ),

    FOREING KEY (rule_id)   REFERENCE chat_rule(id),
    FOREING KEY (chat_id)   REFERENCE chat(id),
    FOREING KEY (server_id) REFERENCE server(id)
);

CREATE INDEX idx_chat_chatname ON char(chatname)
