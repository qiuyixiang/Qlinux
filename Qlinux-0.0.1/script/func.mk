# This Makefile used to define some helper function


### Makefile Function Definition 
# Define Some Global Auxiliary Function

# Check Whether The Directory Exists
# 	$(1):		the file path
define dir_check
	if [ ! -e $(1) ] || [ ! -d $(1) ]; then 	\
		mkdir -p $(1); 							\
	fi
endef

# This Helper function used to check whether the file exists if doesn't exist 
# it will create execute some special command
#	$(1):		the file path
#	$(2):		the executable command
define file_check
	if [ ! -e $(1) ]; then 	\
		$(2);				\
	fi
endef

# Helper function same as echo
define print
	echo "$(1)"
endef
