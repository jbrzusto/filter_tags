# filter_tags

Most motus users do **NOT** need this.  Those who do can obtain the executable code via
the [sensorgnome-R-package](https://github.com/jbrzusto/sensorgnome-R-package)

Filter a stream of (Lotek tagID, timestamp) pairs given a database of known
(Lotek tagID, burstInterval) pairs.  This code supports filtering of
Lotek .DTA files by users of their receivers.


- used by `dta2sg()` and `filterTags()` from [sensorgnome-R-package](https://github.com/jbrzusto/sensorgnome-R-package)

- deprecated in favour of direct handling of Lotek .DTA records by `find_tags_motus`
  from [find_tags](https://github.com/jbrzusto/find_tags)

- might be reinstated as preferred algorithm if/when detection of Lotek tag IDs moves upstream
  to SG receivers (as it already is on Lotek receivers)
