#include <string>
/*
If there are any changes please update this.
*/

const std::string USER_MAUAL = R"(_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
| open <path>											
| Load the file into the memory. Informs in case of		
| usnaved changes.										
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
| validate											
| Checks if the opened JSON file is valid. If there are
| any issues, the program will indicate what and where
| the problem is.									
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
| print													
| Display the content of the JSON file in a human-		
| readable format										
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| search <key>											
| Look for data stored under the specified key. The key	
| can be nested at any level in the JSON document.		
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| contains <value>										
| Check if the JSON object contains the specified value.
| Values can be nested; types are respected (e.g., 19 in
| "Born in 1998", not in number 1998).					
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| set <path> <string>									
| Replace value at path with string if path exists &	
| string's valid JSON. Report errors otherwise.			
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| create <path> <string>								
| Adds new element at path with given string as value.	
| Reports errors if path exists or string's invalid JSON
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| delete <path>											
| Delete element at path if it exists; notify errors.	
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| move <from> <to>										
| Move all elements from <from> path to <to> path.		
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
| save [<path>]                                         
| saveas <file> [<path>]                                
| Save current object to specified path or file, if it  
| exists. If no <path> provided, save entire object in  
| memory.                                               
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _	
| exit													
| Exit the application. Notify for unsaved changes.		
| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
)";