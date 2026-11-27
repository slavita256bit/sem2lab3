// Оформление отчётов по образцу СТП 01-2024 БГУИР.
#let lab-style(body) = {
  let line-step = 18pt
  let leading = line-step - 14pt
  let blank-line = line-step + leading

  set page(
    paper: "a4",
    margin: (left: 30mm, right: 15mm, top: 20mm, bottom: 20mm),
    footer-descent: 20mm - 10mm - 0.8 * 14pt,
    footer: context {
      if counter(page).get().first() > 1 {
        align(right, counter(page).display("1"))
      }
    },
  )
  set text(font: "Times New Roman", size: 14pt, lang: "ru", region: "by",
    overhang: false, top-edge: 0.8em, bottom-edge: -0.2em)
  set par(justify: true, leading: leading, spacing: leading,
    first-line-indent: (amount: 12.5mm, all: true))
  show heading: it => block(above: blank-line, below: blank-line, sticky: true, width: 100%, {
    set par(first-line-indent: 0pt, justify: false)
    align(center, text(size: 14pt, weight: "bold", hyphenate: false, upper(it.body)))
  })
  show list: it => {
    for (i, item) in it.children.enumerate() {
      let punctuation = if i == it.children.len() - 1 [.] else [;]
      par()[– #item.body#punctuation]
    }
  }
  show enum: it => {
    for (i, item) in it.children.enumerate() {
      par()[#(i + 1) #item.body]
    }
  }
  show figure.where(kind: table): set figure(supplement: [Таблица], numbering: "1", gap: leading)
  show figure.where(kind: table): set block(above: blank-line, below: blank-line)
  show figure.where(kind: table): set figure.caption(position: top, separator: [ – ])
  show figure.caption: set align(left)
  show figure.caption: set par(first-line-indent: 0pt, justify: false)
  show table: set par(first-line-indent: 0pt, justify: false)
  set table(stroke: 0.5pt, inset: (x: 0.3em, y: 0.25em))
  show raw: set text(font: ("Courier New", "DejaVu Sans Mono"), size: 12pt)
  body
}

#let lab-title(number, topic) = {
  set par(first-line-indent: 0pt, justify: false)
  set text(hyphenate: false)
  align(center)[
    Министерство образования Республики Беларусь

    #v(18pt)
    Учреждение образования \
    БЕЛОРУССКИЙ ГОСУДАРСТВЕННЫЙ УНИВЕРСИТЕТ \
    ИНФОРМАТИКИ И РАДИОЭЛЕКТРОНИКИ
  ]

  v(18pt)
  grid(
    columns: (auto, 1fr),
    column-gutter: 1em,
    row-gutter: 4pt,
    [Факультет], [компьютерных систем и сетей],
    [Кафедра], [электронных вычислительных машин],
  )

  v(1fr)
  align(center)[
    ОТЧЁТ \
    по лабораторной работе №~#number \
    по дисциплине «Программирование на языках высокого уровня» \
    на тему \
    «#topic»
  ]

  v(1fr)
  align(right, block(width: 8.5cm, align(left)[
    Студент гр. 550503 \
    Ермаков В. С.

    #v(18pt)
    Руководитель \
    преподаватель Ковальчук А. М.
  ]))

  v(1fr)
  align(center)[Минск 2026]
  pagebreak()
}
