CREATE TABLE friendship (
    profile1_id BIGINT NOT NULL,
    profile2_id BIGINT NOT NULL,

    PRIMARY KEY (profile1_id, profile2_id)

    FOREING KEY (profile1_id) REFERENCES profile(id),
    FOREING KEY (profile2_id) REFERENCES profile(id)
);

CREATE INDEX idx_friendship_profile1_id ON friendship(profile1_id);
CREATE INDEX idx_friendship_profile2_id ON friendship(profile2_id);
