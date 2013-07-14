CREATE TABLE Users (
   id int NOT NULL, 
   username text(50),
   fullname text(250),
   gender char,
   PRIMARY KEY (id)
);

CREATE TABLE Posts (
   id int NOT NULL PRIMARY KEY,
   user_id int NOT NULL FOREIGN KEY REFERENCES Users(id),
   content text(250)
);