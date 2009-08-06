// Item 15:  Provide access to raw resources in resource-managing classes.

/*
 APIs often require access to raw resources, so each RAII class should offer a way to get at the resource it manages.

 Access may be via explicit conversion or implicit conversion. In general, explicit conversion is safer, 
 but implicit conversion is more convenient for clients.
 */
 

