CREATE TABLE Users (
   id int NOT NULL AUTO_INCREMENT, 
   username text(50) DEFAULT "hello",
   fullname text(250),
   gender char DEFAULT 'j',
   PRIMARY KEY (id)
);

CREATE TABLE Posts (
   id int NOT NULL PRIMARY KEY,
   user_id int NOT NULL FOREIGN KEY REFERENCES Users(id),
   content text(250) DEFAULT "this is the default post..."
);

CREATE TABLE Likes (
   user_id int NOT NULL FOREIGN KEY REFERENCES Users(id),
   post_id int NOT NULL,
   FOREIGN KEY (post_id) REFERENCES Posts(id)
);