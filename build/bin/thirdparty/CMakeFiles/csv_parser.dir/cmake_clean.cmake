file(REMOVE_RECURSE
  "../../lib/libcsv_parser.a"
  "../../lib/libcsv_parser.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/csv_parser.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
