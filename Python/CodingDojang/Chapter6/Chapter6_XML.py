from xml.etree.ElementTree import Element, SubElement, dump

blog = Element("blog")
subject = Element("subject")
author = Element("author")
content = Element("content")

subject.text = "Why python?"
author.text = "Eric"
content.text = "Life is too short, You need Python"

blog.attrib['date'] = "20151231"
blog.append(subject); blog.append(author); blog.append(content)

def indent(elem, level = 0):
    i = "\n" + level*" "

    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + " "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i

        for elem in elem:
            indent(elem, level + 1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else :
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

indent(blog)
dump(blog)