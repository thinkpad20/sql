SELECT u.username, p.content from Users u, Posts p WHERE u.id = 1;

SELECT u.username, p.content
   from Users u
   INNER JOIN Posts p
   ON u.id = p.user_id
   WHERE a != -3 and b > 5 or c = a;