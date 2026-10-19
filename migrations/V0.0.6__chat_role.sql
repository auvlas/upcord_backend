CREATE TABLE chat_rule (
    id                 INTEGER  PRIMARY KEY AUTOINCREMENT,
    role_id            TEXT     NOT NULL,
    can_send_voice     BOOLEAN  DEFAULT FALSE,
    can_send_image     BOOLEAN  DEFAULT FALSE,
    can_send_message   BOOLEAN  DEFAULT FALSE,
    can_delete_message BOOLEAN  DEFAULT FALSE,
    can_invite_users   BOOLEAN  DEFAULT FALSE,
    can_delete_users   BOOLEAN  DEFAULT FALSE,
    created_at         DATETIME DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (role_id) REFERENCES chat(chat_role(id).chat_id) ON DELETE CASCADE
);

CREATE INDEX idx_chat_role_chat_id ON chat_role(chat_id);
