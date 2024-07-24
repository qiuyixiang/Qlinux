# This Makefile used to define some helper function


### Makefile Function Definition 
# Define Some Global Auxiliary Function

# Check Whether The Directory Exists
define dir_check
	if [ ! -e $(1) ] || [ ! -d $(1) ]; then 	\
		mkdir -p $(1); 							\
	fi
endef

# Helper function same as echo
define print
	echo "$(1)"
endef