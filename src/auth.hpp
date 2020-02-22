
#define CHECK_AUTH                                              \
do{                                                             \
   if(req.header("Authorization") != "Basic dGVzdDp0ZXN0"){     \
        res.set_status(401);                                    \
	    BOOST_LOG_TRIVIAL(trace) << "Feild Auth";               \
        return;                                                 \
   }                                                            \
   BOOST_LOG_TRIVIAL(trace) << "Succed Auth";                   \
}while(false)   

