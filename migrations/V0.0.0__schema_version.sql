CREATE TABLE IF NOT EXISTS schema_version (
    id            INTEGER PRIMARY KEY AUTOINCREMENT,
    version_major INTEGER NOT NULL,
    version_minor INTEGER NOT NULL,
    version_file  INTEGER NOT NULL,
    applied_at    DATETIME DEFAULT CURRENT_TIMESTAMP
);
