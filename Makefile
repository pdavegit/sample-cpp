all:
	g++ -static -o ./main_app-static ./main.cpp -L/usr/lib -lboost_iostreams -lboost_program_options -lboost_timer -lboost_filesystem -lboost_date_time -lboost_regex -lboost_system -lboost_thread-mt -lboost_chrono -lgcov -llog4cxx -lapr-1 -lz -laprutil-1 -lexpat
	g++         -o ./main_app ./main.cpp -L/usr/lib -lboost_iostreams -lboost_program_options -lboost_timer -lboost_filesystem -lboost_date_time -lboost_regex -lboost_system -lboost_thread-mt -lboost_chrono -lgcov -llog4cxx -lapr-1 -lz -laprutil-1 -lexpat

