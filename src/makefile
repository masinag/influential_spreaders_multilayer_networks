all: aggPR addPR verPR aggKCore sumKCore multiKCore aggDeg mlPowerCommunityIndex \
	laPowerCommunityIndex alPowerCommunityIndex lsPowerCommunityIndex verBC

aggPR:
	g++ -std=c++14 aggPageRank/main.cpp aggPageRank/aggPR.cpp utils/Graph.cpp \
		utils/common.cpp \
		-o aggPageRank/aggPR.out
addPR:
	g++ -std=c++14 addPageRank/main.cpp addPageRank/addPR.cpp utils/Graph.cpp \
		utils/Multilayer.cpp aggPageRank/aggPR.cpp utils/common.cpp \
		-o addPageRank/addPR.out

verPR:
	g++ -std=c++14 verPageRank/main.cpp verPageRank/verPR.cpp utils/Multilayer.cpp \
		utils/Graph.cpp utils/common.cpp \
		-o verPageRank/verPR.out

aggKCore:
	g++ -std=c++14 aggCore/main.cpp aggCore/aggCore.cpp utils/Graph.cpp \
		utils/common.cpp \
		-o aggCore/aggCore.out
sumKCore:
	g++ -std=c++14 sumCore/main.cpp sumCore/sumCore.cpp utils/Graph.cpp \
		aggCore/aggCore.cpp utils/Multilayer.cpp utils/common.cpp \
		-o sumCore/sumCore.out
multiKCore:
	g++ -std=c++14 multiCore/main.cpp multiCore/multiCore.cpp utils/Multilayer.cpp \
		utils/Graph.cpp utils/common.cpp \
		-o multiCore/multiCore.out

aggDeg:
	g++ -std=c++14 aggDegree/main.cpp aggDegree/aggDeg.cpp utils/Graph.cpp \
		utils/common.cpp \
		-o aggDegree/aggDeg.out

mlPowerCommunityIndex:
	g++ -std=c++14 mlPCI/main.cpp mlPCI/mlPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o mlPCI/mlPCI.out

laPowerCommunityIndex:
	g++ -std=c++14 laPCI/main.cpp laPCI/laPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o laPCI/laPCI.out

alPowerCommunityIndex:
	g++ -std=c++14 alPCI/main.cpp alPCI/alPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o alPCI/alPCI.out

lsPowerCommunityIndex:
	g++ -std=c++14 lsPCI/main.cpp lsPCI/lsPCI.cpp \
		utils/Multilayer.cpp utils/Graph.cpp utils/common.cpp \
		-o lsPCI/lsPCI.out

verBC:
	g++ -std=c++14 verBetweenness/main.cpp verBetweenness/verBC.cpp utils/Multilayer.cpp \
		utils/Graph.cpp utils/common.cpp \
		-o verBetweenness/verBC.out


spread:
	g++ -std=c++14 evaluation/spread_process.cpp utils/Graph.cpp \
		utils/common.cpp utils/Multilayer.cpp evaluation/io.cpp \
		-o evaluation/spread.out

run_alg:
	g++ -std=c++14 evaluation/run_algorithms.cpp utils/Graph.cpp \
		utils/common.cpp utils/Multilayer.cpp evaluation/io.cpp \
		addPageRank/addPR.cpp aggCore/aggCore.cpp aggDegree/aggDeg.cpp \
		aggPageRank/aggPR.cpp alPCI/alPCI.cpp laPCI/laPCI.cpp lsPCI/lsPCI.cpp \
		mlPCI/mlPCI.cpp multiCore/multiCore.cpp sumCore/sumCore.cpp verBetweenness/verBC.cpp \
		verPageRank/verPR.cpp \
		-o evaluation/run_alg.out