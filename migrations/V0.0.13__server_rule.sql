CREATE TABLE server_rule (
    id                        BIGINT      PRIMARY KEY AUTOINCREMENT,
    name                      VARCHAR(50) NOT NULL,
    server_id                 BIGINT      NOT NULL,
    chat_rule_id              BIGINT      NOT NULL,
    can_create_category       BOOLEAN     DEFAULT FALSE,
    renamed_at                DATETIME    DEFAULT NULL,
    updated_at                DATETIME    DEFAULT NULL,
    created_at                DATETIME    DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (chat_id)     REFERENCES  chat(id)
        ON DELETE CASCADE
);

CREATE INDEX idx_server_rule_server_id
    ON server_rule(server_id);
