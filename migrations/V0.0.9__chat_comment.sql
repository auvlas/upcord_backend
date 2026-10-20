CREATE TABLE chat_comment (
    id          BIGINT     PRIMARY KEY AUTOINCREMENT,
    message_id  BIGINT     NOT NULL,
    chat_id     BIGINT     NOT NULL,

    FOREING KEY message_id REFERENCES chat_message(id)
        ON DELETE CASCADE,
    FOREING KEY chat_id    REFERENCES chat(id)
        ON DELETE CASCADE
);

CREATE TABLE idx_chat_comment_message_id
    ON chat_comment(message_id);
