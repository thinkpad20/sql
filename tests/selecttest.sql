SELECT "User: " || u.username, p.content from Users u, Posts p WHERE u.id = 1;

SELECT (u.age * 4)/25 as b, p.content
   from Users u
   INNER JOIN Posts p
   ON u.id = p.user_id
   WHERE a != -3 and b > 5 or c = a;