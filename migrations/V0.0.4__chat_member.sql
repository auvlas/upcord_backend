CREATE TABLE chat_member (
    chat_id     INTEGER  NOT NULL,
    profile_id  INTEGER  NOT NULL,
    name        TEXT,
    avatar      TEXT,
    joined_at   DATETIME DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (chat_id, profile_id), 

    FOREIGN KEY (chat_id) REFERENCES chat(id) ON DELETE CASCADE,
    FOREIGN KEY (profile_id) REFERENCES user_profile(id) ON DELETE CASCADE
);

CREATE INDEX idx_chat_member_profile_id ON chat_member(profile_id);
