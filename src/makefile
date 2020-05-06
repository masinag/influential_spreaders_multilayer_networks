
aggPR:
	g++ aggPageRank/main.cpp aggPageRank/aggPR.cpp utils/Aggregate.cpp \
		utils/common.cpp \
		-o aggPageRank/aggPR.out
aggKCore:
	g++ aggCore/main.cpp aggCore/aggCore.cpp utils/Aggregate.cpp \
		utils/common.cpp \
		-o aggCore/aggCore.out
sumKCore:
	g++ sumCore/main.cpp sumCore/sumCore.cpp utils/Aggregate.cpp \
		aggCore/aggCore.cpp utils/Multilayer.cpp utils/common.cpp \
		-o sumCore/sumCore.out

aggDeg:
	g++ aggDegree/main.cpp aggDegree/aggDeg.cpp utils/Aggregate.cpp \
		utils/common.cpp \
		-o aggDegree/aggDeg.out

spread:
	g++ spread_process/spread_process.cpp utils/Aggregate.cpp \
		utils/common.cpp utils/Multilayer.cpp \
		-o spread_process/spread.out