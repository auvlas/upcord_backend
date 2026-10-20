CREATE TABLE friend (
    profile1_id BIGINT NOT NULL,
    profile2_id BIGINT NOT NULL,

    PRIMARY KEY (profile1_id, profile2_id)

    FOREING KEY (profile1_id) REFERENCES profile(id),
    FOREING KEY (profile2_id) REFERENCES profile(id)
);

CREATE INDEX idx_friend_profile1_id ON friend(profile1_id);
CREATE INDEX idx_friend_profile2_id ON friend(profile2_id);
