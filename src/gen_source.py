print "Gen files ..."
includes = open("gen/includes.hpp", "w")
fileSet = []
with open("/s/doc/restfull.txt", "r") as f:
    for l in f:
        if l.find("Path: ") == -1: continue
        sp = l.split("/")
        if len(sp) < 1 : continue
        print sp[1]
        with open("gen/%s.hpp"%sp[1],"w") as g:
            g.write("#pragma once\n")
            g.write("#include <nlohmann/json.hpp>\n")
            g.write("#include <served/served.hpp>\n")
            g.write("#include \"main_storage.hpp\"\n\n")
        with open("gen/%s.cpp"%sp[1],"w") as g:
            g.write("#include \"auth.hpp\"\n")
            g.write("#include \"%s.hpp\"\n\n"%sp[1])
            g.write("extern MainStorage st;\n")
        if sp[1] not in fileSet:
            includes.write("#include \"%s.hpp\"\n"%sp[1])
            fileSet.append(sp[1])

includes.close()
print "Fill files ..."
route    = open("gen/routes.hpp", "w")

fileSet = []

with open("/s/doc/restfull.txt", "r") as f:
    for l in f:
        if l.find("Path: ") == -1: continue
        sp = l.split("/")
        if len(sp) < 1 : continue
        name = ""
        route_str = "/"
        i = 1
        while i < len(sp):
            spl = sp[i].replace("\n","").replace("{","").replace("}","")
            name += spl 
            route_str += spl
            if i < len(sp)-1:
                name +=  '_'
                route_str += '/'
            i += 1
        if name in fileSet: continue
        fileSet.append(name)

        print "in %s func name %s Line:%s"%(sp[1], name, l)

        route.write("BOOST_LOG_TRIVIAL(trace) << \"Add route %s\";\n"%(route_str))
        route.write("mux.handle(\"%s\").get(%s);\n"%(route_str, name))
        with open("gen/%s.hpp"%sp[1],"a") as g:
            g.write("void %s(served::response &, const served::request &);\n"%name)
            
        with open("gen/%s.cpp"%sp[1],"a") as g:
            g.write("void %s(served::response &res, const served::request &req)\n"%name)
            g.write("{\n")
            g.write("\tBOOST_LOG_TRIVIAL(trace) << \"Start %s\";\n"%name)
            g.write("\tCHECK_AUTH;\n")
            g.write("}\n")

route.close()
