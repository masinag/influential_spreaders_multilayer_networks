all: extract generate

extract: remove_extracted
	mkdir multiplex/extracted
	python3 extract.py

remove_extracted:
	rm -rf multiplex/extracted

generate: remove_generated
	mkdir multilayer/generated
	python3 generate.py

remove_generated:
	rm -rf multilayer/generated
	rm -rf multilayer/plots