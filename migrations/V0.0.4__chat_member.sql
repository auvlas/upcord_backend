CREATE TABLE chat_member (
    chat_id        BIGINT       NOT NULL,
    profile_id     BIGINT,
    name           VARCHAR(50)  DEFAULT NULL,
    avatar         TEXT         DEFAULT NULL,
    created_at     DATETIME     DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY    (chat_id, profile_id), 

    FOREIGN KEY    (chat_id)    REFERENCES chat(id)
        ON DELETE CASCADE,
    FOREIGN KEY    (profile_id) REFERENCES profile(id)
        ON DELETE CASCADE
);

CREATE INDEX idx_chat_member_profile_id ON chat_member(profile_id);
