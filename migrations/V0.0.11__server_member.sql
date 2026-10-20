CREATE TABLE server_member (
    server_id      BIGINT       NOT NULL,
    profile_id     BIGINT       NOT NULL,
    name           VARCHAR(50)  DEFAULT NULL,
    avatar         TEXT         DEFAULT NULL,
    created_at     DATETIME     DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY    (server_id,  profile_id), 

    FOREIGN KEY    (server_id)  REFERENCES server(id)
        ON DELETE CASCADE,
    FOREIGN KEY    (profile_id) REFERENCES profile(id)
        ON DELETE CASCADE
);

CREATE INDEX idx_server_member_profile_id
    ON server_member(profile_id);
