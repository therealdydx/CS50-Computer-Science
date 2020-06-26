select distinct(name) from people
join stars on stars.person_id = people.id
join movies on movies.id = stars.movie_id
where movies.year = 2004
order by people.birth asc