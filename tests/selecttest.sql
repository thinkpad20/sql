SELECT DISTINCT "User: " || u.username, p.content from Users u, Posts p WHERE u.id = 1;

SELECT COUNT(u.username) from Users u NATURAL JOIN Tweets t;

SELECT (u.age * 4)/25 as b, p.content
   from Users u
   INNER JOIN Posts p
   ON u.id = p.user_id
   FULL OUTER JOIN q
   ON q.qux < (u.baz * p.puz) and ((78 + p.biz * q.qux) > 3 or q.zippy > 5)
   WHERE a != -3 and b > 5.76 or c = a and name in ("tom", "dick", "harry")
   GROUP BY p.content ORDER BY foo;