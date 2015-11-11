##############################################
# Fall 2015, CIS 314 Computer Organization   #
# Major Class Project                        #
##############################################

# This tests for function calls #############
# By calculating (a*b) , (a* (b-1)), ...(a*1)
#############################################
	
# Setting the stack pointer #
	   addi $t1, $0, 256
	   addi $t2, $0, 32
	   add $t3, $t1, $t2
	# branch to end
#############################

