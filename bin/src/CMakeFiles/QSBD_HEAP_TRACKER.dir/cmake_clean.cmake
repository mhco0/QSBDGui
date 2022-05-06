file(REMOVE_RECURSE
  "../../lib/libQSBD_HEAP_TRACKER.a"
  "../../lib/libQSBD_HEAP_TRACKER.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/QSBD_HEAP_TRACKER.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
