select movies.title, ratings.rating from movies
join ratings on ratings.movie_id = movies.id
where year = 2010 order by ratings.rating desc, movies.title;