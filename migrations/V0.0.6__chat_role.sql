CREATE TABLE chat_role (
    id         BIGINT      PRIMARY KEY AUTOINCREMENT,
    chat_id    BIGINT      NOT NULL,
    rule_id    BIGINT      DEFAULT NULL,
    name       VARCHAR(50) NOT NULL,
    color      CHAR(7)     DEFAULT NULL,
    renamed_at DATETIME    DEFAULT NULL,
    updated_at DATETIME    DEFAULT NULL,
    created_at DATETIME    DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (chat_id)  REFERENCES chat(id)
        ON DELETE CASCADE,
    FOREIGN KEY (rule_id)  REFERENCES chat_rule(id)
);

CREATE INDEX idx_chat_rule_chat_id ON chat_role(chat_id);
