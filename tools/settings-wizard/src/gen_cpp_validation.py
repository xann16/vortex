#from cpp_utils import get_class_name, get_namespace, begin_namespace, end_namespace, add_blank, add_line, add_block_comment, add_method_declaration, add_method_definition, begin_test_case, end_test_case, add_require
#from gen_utils import to_pascal_case
#from typing import Any

'''

VALIDATION:

 - is_set (a.k.a is_required)
 - nonempty
 - range(min=None,max=None,step=None)
 - unique(property_mapping=None) [arrays only]

 + (*) post-validation

 BASIC PARSING:

 - validator name
 - optional empty parentheses
 - parentheses with equality sign seperated kwargs
 - , - and
 - | - or

EXTRA PARSING:

 - inside {{ }}
 - # - constants
 - @ - properties (by paths?)
 - $ - environment variables
 - other - operators or built in functions
 - for all symbols - optional - ':<value>' - default value if reference is not specified; null by default; or ! - if undefined - fail validation



'''
