# Influential Spreaders In Multilayer Networks

This repository includes the code of the project I conducted for my Bachelor's thesis.

The project aims to identify the nodes called *influential spreaders* in multilayer networks (or graphs).

*Influential spreaders* are those nodes that, during a process of diffusion of
information in the network, allow to reach the largest portion of the network.
Identifying these nodes is particularly useful because they can be exploited to
maximize the diffusion of information or, on the contrary,
isolated if it is desired that it remains as confined as possible.

A [*multilayer network*](https://en.wikipedia.org/wiki/Multidimensional_network) allows to represent different kinds of links,
generalizing the concept of *graph* where all links are of the same type.

Information can propagate with diverse probabilities on different types of links, making this problem particularly challenging.

Influential spreaders can be identified by simulating the diffusion processes, but this process is very expensive, and hence not applicable to very large networks.
We tried alternative approaches to identify them by analyzing network topology through several centrality algorithms, adapted to the multilayer case.

These algorithms were applied to different types of multilayer networks:
multiplex networks extracted from biological and
social datasets and multilayer networks randomly generated
starting from graphs derived from peer-to-peer applications.

The centrality values ​​of the nodes returned by each algorithm were
compared with the real ones, obtained by simulating diffusion processes
in the various networks. In this way, it was possible to assign to each algorithm
a score obtained on each network and thus identify which algorithms
can be used to find the influential spreaders in a multilayer network.
Two of the tested algorithms obtained good performances on all the
analyzed networks, while the performances of the others were poor or fluctuating.

The thesis and the slides (in Italian) are contained in the `doc/` folder.

## Requirements
- python3
- c++14

# Run
- install requirements.txt
- see src/makefile
