CREATE TABLE profile (
    id          BIGINT      PRIMARY KEY AUTOINCREMENT,
    user_id     BIGINT      NOT NULL,
    name        VARCHAR(50) NOT NULL,
    first_name  VARCHAR(50) DEFAULT NULL,
    last_name   VARCHAR(50) DEFAULT NULL,
    father_name VARCHAR(50) DEFAULT NULL,
    bio         TEXT        DEFAULT NULL,
    username    VARCHAR(50) DEFAULT NULL UNIQUE,
    phone       VARCHAR(15) DEFAULT NULL,
    avatar      TEXT        DEFAULT NULL,
    created_at  DATETIME    DEFAULT CURRENT_TIMESTAMP,
    birth_date  DATE        DEFAULT NULL,

    FOREIGN KEY (user_id)   REFERENCES user(id)
        ON DELETE CASCADE
);

CREATE INDEX idx_profile_user_id  ON profile(user_id)
CREATE INDEX idx_profile_username ON profile(username)
