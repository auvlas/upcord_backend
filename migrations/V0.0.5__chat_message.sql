CREATE TABLE IF NOT EXISTS chat_message (
    id          BIGINT      PRIMARY KEY AUTOINCREMENT,
    chat_id     BIGINT      NOT NULL,
    sender_id   BIGINT,
    text        TEXT        NOT NULL,
    created_at  DATETIME    DEFAULT CURRENT_TIMESTAMP,
    
    FOREIGN KEY (chat_id)   REFERENCES chat(id)
        ON DELETE CASCADE,
    FOREIGN KEY (sender_id) REFERENCES chat_member(id)
        ON DELETE CASCADE
);

CREATE INDEX idx_chat_message_chat_time
    ON chat_message(chat_id, created_at);
