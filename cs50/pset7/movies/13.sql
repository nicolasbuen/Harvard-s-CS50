SELECT distinct(name) FROM people
JOIN stars ON people.id = stars.person_id 
JOIN movies on stars.movie_id = movies.id 
WHERE movies.title IN(
SELECT DISTINCT(title) FROM movies
JOIN stars ON movies.id = stars.movie_id 
JOIN people ON stars.person_id = people.id 
WHERE people.name = "Kevin Bacon" and people.birth = 1958)
AND NOT (name == "Kevin Bacon")