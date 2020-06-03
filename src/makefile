all: aggPR addPR verPR aggKCore sumKCore multiKCore aggDeg mlPowerCommunityIndex \
	laPowerCommunityIndex alPowerCommunityIndex lsPowerCommunityIndex verBC

aggPR:
	g++ -std=c++11 aggPageRank/main.cpp aggPageRank/aggPR.cpp utils/Graph.cpp \
		utils/common.cpp \
		-o aggPageRank/aggPR.out
addPR:
	g++ -std=c++11 addPageRank/main.cpp addPageRank/addPR.cpp utils/Graph.cpp \
		utils/Multilayer.cpp aggPageRank/aggPR.cpp utils/common.cpp \
		-o addPageRank/addPR.out

verPR:
	g++ -std=c++11 verPageRank/main.cpp verPageRank/verPR.cpp utils/Multilayer.cpp \
		utils/Graph.cpp utils/common.cpp \
		-o verPageRank/verPR.out

aggKCore:
	g++ -std=c++11 aggCore/main.cpp aggCore/aggCore.cpp utils/Graph.cpp \
		utils/common.cpp \
		-o aggCore/aggCore.out
sumKCore:
	g++ -std=c++11 sumCore/main.cpp sumCore/sumCore.cpp utils/Graph.cpp \
		aggCore/aggCore.cpp utils/Multilayer.cpp utils/common.cpp \
		-o sumCore/sumCore.out
multiKCore:
	g++ -std=c++11 multiCore/main.cpp multiCore/multiCore.cpp utils/Multilayer.cpp \
		utils/Graph.cpp utils/common.cpp \
		-o multiCore/multiCore.out

aggDeg:
	g++ -std=c++11 aggDegree/main.cpp aggDegree/aggDeg.cpp utils/Graph.cpp \
		utils/common.cpp \
		-o aggDegree/aggDeg.out

mlPowerCommunityIndex:
	g++ -std=c++11 mlPCI/main.cpp mlPCI/mlPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o mlPCI/mlPCI.out

laPowerCommunityIndex:
	g++ -std=c++11 laPCI/main.cpp laPCI/laPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o laPCI/laPCI.out

alPowerCommunityIndex:
	g++ -std=c++11 alPCI/main.cpp alPCI/alPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o alPCI/alPCI.out

lsPowerCommunityIndex:
	g++ -std=c++11 lsPCI/main.cpp lsPCI/lsPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o lsPCI/lsPCI.out

verBC:
	g++ -std=c++11 verBetweenness/main.cpp verBetweenness/verBC.cpp utils/Multilayer.cpp \
		utils/Graph.cpp utils/common.cpp \
		-o verBetweenness/verBC.out


spread:
	g++ -std=c++11 spread_process/spread_process.cpp utils/Graph.cpp \
		utils/common.cpp utils/Multilayer.cpp spread_process/io.cpp \
		-o spread_process/spread.out