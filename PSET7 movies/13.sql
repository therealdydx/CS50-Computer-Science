select distinct(name) from people
join stars on people.id = stars.person_id
join movies on stars.movie_id = movies.id
where movies.title IN(select distinct(movies.title) from people
join stars on people.id = stars.person_id
join movies on stars.movie_id = movies.id
where people.name = "Kevin Bacon" and people.birth = 1958) and people.name != "Kevin Bacon";

/*
select distinct(name) from people
where name is not "Kevin Bacon"
and id in
(select person_id from stars
where stars.movie_id in
(select stars.movie_id from stars
where stars.person_id =
(select id from people
where name = "Kevin Bacon" and people.birth = 1958)));
*/
