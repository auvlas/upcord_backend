CREATE TABLE server_role (
    id         BIGINT       PRIMARY KEY AUTOINCREMENT,
    server_id  BIGINT       NOT NULL,
    rule_id    BIGINT       DEFAULT NULL,
    name       VARCHAR(50)  NOT NULL,
    color      CHAR(7)      DEFAULT NULL,
    renamed_at DATETIME     DEFAULT NULL,
    updated_at DATETIME     DEFAULT NULL,
    created_at DATETIME     DEFAULT CURRENT_TIMESTAMP,

    FOREIGN KEY (server_id) REFERENCES server(id)
        ON DELETE CASCADE,
    FOREIGN KEY (rule_id)   REFERENCES server_rule(id)
);

CREATE INDEX idx_server_role_server_id
    ON server_role(server_id);
