CREATE TABLE Users (
   id int NOT NULL AUTO_INCREMENT, 
   username varchar(50) DEFAULT "hello",
   fullname text(250),
   gender char DEFAULT 'M',
   PRIMARY KEY (id)
);

CREATE TABLE Posts (
   id integer NOT NULL PRIMARY KEY,
   user_id int NOT NULL FOREIGN KEY REFERENCES Users(id),
   content text(250) DEFAULT "this is the default post..."
);

CREATE TABLE Likes (
   user_id int NOT NULL FOREIGN KEY REFERENCES Users(id),
   post_id int NOT NULL,
   FOREIGN KEY (post_id) REFERENCES Posts(id)
);

CREATE TABLE Hashtag (
   content text(250) CHECK a != 3
);