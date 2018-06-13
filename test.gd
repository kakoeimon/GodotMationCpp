extends Node

# class member variables go here, for example:
# var a = 2
# var b = "textvar"

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	var godotmation = get_child(0)
	godotmation.setup()
	#print(godotmation.get_GM_number(0))
	godotmation.start()
	#print("after start : " + str(godotmation.get_GM_number(0)))
	#print("after start : " + str(godotmation.get_GM_number(1)))
	var time = OS.get_ticks_msec()
	for i in range(0):
		#print(godotmation.get_GM_number(7))
		godotmation.tick()
		
	print(OS.get_ticks_msec() - time)
	pass

func test_number():
	return 62
