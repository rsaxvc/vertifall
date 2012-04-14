id = local_id()
print( "id:", id )
if object_class( id ) == 1 then
	print( "class:", object_class_name( id ) )
	tc = global_tick_count()
	object_set_velocity(  4 * math.cos( tc ), 4 * math.sin( tc ), 0, id ) 
end

--print (global_tick_count())
--print (global_num_objects())
--n_obs = global_num_objects() - 1
--for iter=0,n_obs do
--	print ("examining object#",iter)
--	print ("\tLocation:", object_location( iter ) )
--	print ("\tSpeed   :", object_speed( iter ) )
--	print ("\tName    :", object_name( iter ) )
--	print ("\tClass   :", object_class_name( iter ) ) 
--end
