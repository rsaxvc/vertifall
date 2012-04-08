n_obs = num_objects() - 1
for iter=0,n_obs do
	print ("examining object#",iter)
	print ("\tLocation:", object_location( iter ) )
	print ("\tSpeed   :", object_speed( iter ) )
	print ("\tName    :", object_name( iter ) )
	print ("\tClass   :", object_class_name( iter ) ) 
end
