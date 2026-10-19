CREATE TABLE profile (
    id          INTEGER  PRIMARY KEY AUTOINCREMENT,
    user_id     INTEGER  NOT NULL,
    name        TEXT,
    first_name  TEXT,
    last_name   TEXT,
    father_name TEXT,
    bio         TEXT,
    username    TEXT     UNIQUE,
    phone       TEXT,
    avatar      TEXT,
    created_at  DATETIME DEFAULT CURRENT_TIMESTAMP,
    birth_date  DATE

    FOREIGN KEY (user_id) REFERENCES user (id)
        ON DELETE CASCADE
);

CREATE INDEX idx_profile_user_id  ON profile(user_id)
CREATE INDEX idx_profile_username ON user(username)
